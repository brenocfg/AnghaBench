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
typedef  int u16 ;
struct max2175 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max2175_write (struct max2175*,int,int const) ; 
 int /*<<< orphan*/  max2175_write_bit (struct max2175*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_write_bits (struct max2175*,int,int,int,int) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int,int) ; 

__attribute__((used)) static void max2175_set_filter_coeffs(struct max2175 *ctx, u8 m_sel,
				      u8 bank, const u16 *coeffs)
{
	unsigned int i;
	u8 coeff_addr, upper_address = 24;

	mxm_dbg(ctx, "set_filter_coeffs: m_sel %d bank %d\n", m_sel, bank);
	max2175_write_bits(ctx, 114, 5, 4, m_sel);

	if (m_sel == 2)
		upper_address = 12;

	for (i = 0; i < upper_address; i++) {
		coeff_addr = i + bank * 24;
		max2175_write(ctx, 115, coeffs[i] >> 8);
		max2175_write(ctx, 116, coeffs[i]);
		max2175_write(ctx, 117, coeff_addr | 1 << 7);
	}
	max2175_write_bit(ctx, 117, 7, 0);
}