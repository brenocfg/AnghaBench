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
struct etmv4_config {unsigned long vmid_mask0; unsigned long vmid_mask1; int* vmid_val; } ;
struct etmv4_drvdata {int numvmidc; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  vmid_size; struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long ETMv4_EVENT_MASK ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static ssize_t vmid_masks_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t size)
{
	u8 i, j, maskbyte;
	unsigned long val1, val2, mask;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	/*
	 * only implemented when vmid tracing is enabled, i.e. at least one
	 * vmid comparator is implemented and at least 8 bit vmid size
	 */
	if (!drvdata->vmid_size || !drvdata->numvmidc)
		return -EINVAL;
	if (sscanf(buf, "%lx %lx", &val1, &val2) != 2)
		return -EINVAL;

	spin_lock(&drvdata->spinlock);

	/*
	 * each byte[0..3] controls mask value applied to vmid
	 * comparator[0..3]
	 */
	switch (drvdata->numvmidc) {
	case 0x1:
		/* COMP0, bits[7:0] */
		config->vmid_mask0 = val1 & 0xFF;
		break;
	case 0x2:
		/* COMP1, bits[15:8] */
		config->vmid_mask0 = val1 & 0xFFFF;
		break;
	case 0x3:
		/* COMP2, bits[23:16] */
		config->vmid_mask0 = val1 & 0xFFFFFF;
		break;
	case 0x4:
		/* COMP3, bits[31:24] */
		config->vmid_mask0 = val1;
		break;
	case 0x5:
		/* COMP4, bits[7:0] */
		config->vmid_mask0 = val1;
		config->vmid_mask1 = val2 & 0xFF;
		break;
	case 0x6:
		/* COMP5, bits[15:8] */
		config->vmid_mask0 = val1;
		config->vmid_mask1 = val2 & 0xFFFF;
		break;
	case 0x7:
		/* COMP6, bits[23:16] */
		config->vmid_mask0 = val1;
		config->vmid_mask1 = val2 & 0xFFFFFF;
		break;
	case 0x8:
		/* COMP7, bits[31:24] */
		config->vmid_mask0 = val1;
		config->vmid_mask1 = val2;
		break;
	default:
		break;
	}

	/*
	 * If software sets a mask bit to 1, it must program relevant byte
	 * of vmid comparator value 0x0, otherwise behavior is unpredictable.
	 * For example, if bit[3] of vmid_mask0 is 1, we must clear bits[31:24]
	 * of vmid comparator0 value (corresponding to byte 0) register.
	 */
	mask = config->vmid_mask0;
	for (i = 0; i < drvdata->numvmidc; i++) {
		/* mask value of corresponding vmid comparator */
		maskbyte = mask & ETMv4_EVENT_MASK;
		/*
		 * each bit corresponds to a byte of respective vmid comparator
		 * value register
		 */
		for (j = 0; j < 8; j++) {
			if (maskbyte & 1)
				config->vmid_val[i] &= ~(0xFFUL << (j * 8));
			maskbyte >>= 1;
		}
		/* Select the next vmid comparator mask value */
		if (i == 3)
			/* vmid comparators[4-7] */
			mask = config->vmid_mask1;
		else
			mask >>= 0x8;
	}
	spin_unlock(&drvdata->spinlock);
	return size;
}