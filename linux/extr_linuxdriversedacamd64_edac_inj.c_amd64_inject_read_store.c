#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  section; } ;
struct amd64_pvt {int /*<<< orphan*/  F3; TYPE_1__ injection; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  F10_NB_ARRAY_ADDR ; 
 int /*<<< orphan*/  F10_NB_ARRAY_DATA ; 
 int F10_NB_ARRAY_DRAM ; 
 int SET_NB_ARRAY_ADDR (int /*<<< orphan*/ ) ; 
 int SET_NB_DRAM_INJECTION_READ (TYPE_1__) ; 
 int /*<<< orphan*/  amd64_write_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 struct mem_ctl_info* to_mci (struct device*) ; 

__attribute__((used)) static ssize_t amd64_inject_read_store(struct device *dev,
				       struct device_attribute *mattr,
				       const char *data, size_t count)
{
	struct mem_ctl_info *mci = to_mci(dev);
	struct amd64_pvt *pvt = mci->pvt_info;
	unsigned long value;
	u32 section, word_bits;
	int ret;

	ret = kstrtoul(data, 10, &value);
	if (ret < 0)
		return ret;

	/* Form value to choose 16-byte section of cacheline */
	section = F10_NB_ARRAY_DRAM | SET_NB_ARRAY_ADDR(pvt->injection.section);

	amd64_write_pci_cfg(pvt->F3, F10_NB_ARRAY_ADDR, section);

	word_bits = SET_NB_DRAM_INJECTION_READ(pvt->injection);

	/* Issue 'word' and 'bit' along with the READ request */
	amd64_write_pci_cfg(pvt->F3, F10_NB_ARRAY_DATA, word_bits);

	edac_dbg(0, "section=0x%x word_bits=0x%x\n", section, word_bits);

	return count;
}