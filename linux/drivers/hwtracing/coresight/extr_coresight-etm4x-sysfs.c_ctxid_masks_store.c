#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct etmv4_config {unsigned long ctxid_mask0; unsigned long ctxid_mask1; int* ctxid_pid; } ;
struct etmv4_drvdata {int numcidc; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  ctxid_size; struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long ETMv4_EVENT_MASK ; 
 int /*<<< orphan*/  current ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/ * task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ctxid_masks_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t size)
{
	u8 i, j, maskbyte;
	unsigned long val1, val2, mask;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	/*
	 * Don't use contextID tracing if coming from a PID namespace.  See
	 * comment in ctxid_pid_store().
	 */
	if (task_active_pid_ns(current) != &init_pid_ns)
		return -EINVAL;

	/*
	 * only implemented when ctxid tracing is enabled, i.e. at least one
	 * ctxid comparator is implemented and ctxid is greater than 0 bits
	 * in length
	 */
	if (!drvdata->ctxid_size || !drvdata->numcidc)
		return -EINVAL;
	if (sscanf(buf, "%lx %lx", &val1, &val2) != 2)
		return -EINVAL;

	spin_lock(&drvdata->spinlock);
	/*
	 * each byte[0..3] controls mask value applied to ctxid
	 * comparator[0..3]
	 */
	switch (drvdata->numcidc) {
	case 0x1:
		/* COMP0, bits[7:0] */
		config->ctxid_mask0 = val1 & 0xFF;
		break;
	case 0x2:
		/* COMP1, bits[15:8] */
		config->ctxid_mask0 = val1 & 0xFFFF;
		break;
	case 0x3:
		/* COMP2, bits[23:16] */
		config->ctxid_mask0 = val1 & 0xFFFFFF;
		break;
	case 0x4:
		 /* COMP3, bits[31:24] */
		config->ctxid_mask0 = val1;
		break;
	case 0x5:
		/* COMP4, bits[7:0] */
		config->ctxid_mask0 = val1;
		config->ctxid_mask1 = val2 & 0xFF;
		break;
	case 0x6:
		/* COMP5, bits[15:8] */
		config->ctxid_mask0 = val1;
		config->ctxid_mask1 = val2 & 0xFFFF;
		break;
	case 0x7:
		/* COMP6, bits[23:16] */
		config->ctxid_mask0 = val1;
		config->ctxid_mask1 = val2 & 0xFFFFFF;
		break;
	case 0x8:
		/* COMP7, bits[31:24] */
		config->ctxid_mask0 = val1;
		config->ctxid_mask1 = val2;
		break;
	default:
		break;
	}
	/*
	 * If software sets a mask bit to 1, it must program relevant byte
	 * of ctxid comparator value 0x0, otherwise behavior is unpredictable.
	 * For example, if bit[3] of ctxid_mask0 is 1, we must clear bits[31:24]
	 * of ctxid comparator0 value (corresponding to byte 0) register.
	 */
	mask = config->ctxid_mask0;
	for (i = 0; i < drvdata->numcidc; i++) {
		/* mask value of corresponding ctxid comparator */
		maskbyte = mask & ETMv4_EVENT_MASK;
		/*
		 * each bit corresponds to a byte of respective ctxid comparator
		 * value register
		 */
		for (j = 0; j < 8; j++) {
			if (maskbyte & 1)
				config->ctxid_pid[i] &= ~(0xFFUL << (j * 8));
			maskbyte >>= 1;
		}
		/* Select the next ctxid comparator mask value */
		if (i == 3)
			/* ctxid comparators[4-7] */
			mask = config->ctxid_mask1;
		else
			mask >>= 0x8;
	}

	spin_unlock(&drvdata->spinlock);
	return size;
}