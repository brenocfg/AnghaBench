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
typedef  scalar_t__ u32 ;
struct i2400m_bcf_hdr {int /*<<< orphan*/  module_id; } ;
struct i2400m {TYPE_1__* barker; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ I2400M_SBOOT_BARKER ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
unsigned i2400m_bcf_hdr_match(struct i2400m *i2400m,
			      const struct i2400m_bcf_hdr *bcf_hdr)
{
	u32 barker = le32_to_cpu(i2400m->barker->data[0])
		& 0x7fffffff;
	u32 module_id = le32_to_cpu(bcf_hdr->module_id)
		& 0x7fffffff;	/* high bit used for something else */

	/* special case for 5x50 */
	if (barker == I2400M_SBOOT_BARKER && module_id == 0)
		return 1;
	if (module_id == barker)
		return 1;
	return 0;
}