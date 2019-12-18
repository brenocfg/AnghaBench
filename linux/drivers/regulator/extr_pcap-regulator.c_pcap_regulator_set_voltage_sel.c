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
struct regulator_dev {TYPE_1__* desc; } ;
struct pcap_regulator {int index; int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {int n_voltages; } ;

/* Variables and functions */
 int EINVAL ; 
 int ezx_pcap_set_bits (void*,int /*<<< orphan*/ ,int,unsigned int) ; 
 void* rdev_get_drvdata (struct regulator_dev*) ; 
 size_t rdev_get_id (struct regulator_dev*) ; 
 struct pcap_regulator* vreg_table ; 

__attribute__((used)) static int pcap_regulator_set_voltage_sel(struct regulator_dev *rdev,
					  unsigned selector)
{
	struct pcap_regulator *vreg = &vreg_table[rdev_get_id(rdev)];
	void *pcap = rdev_get_drvdata(rdev);

	/* the regulator doesn't support voltage switching */
	if (rdev->desc->n_voltages == 1)
		return -EINVAL;

	return ezx_pcap_set_bits(pcap, vreg->reg,
				 (rdev->desc->n_voltages - 1) << vreg->index,
				 selector << vreg->index);
}