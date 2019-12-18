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
struct i2400m_bootrom_header {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int I2400M_BRH_SIGNATURE_MASK ; 
 int I2400M_BRH_SIGNATURE_SHIFT ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
unsigned i2400m_brh_get_signature(const struct i2400m_bootrom_header *hdr)
{
	return (le32_to_cpu(hdr->command) & I2400M_BRH_SIGNATURE_MASK)
		>> I2400M_BRH_SIGNATURE_SHIFT;
}