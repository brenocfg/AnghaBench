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
typedef  void* u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 unsigned int ULPRX_LA_SIZE ; 
 int /*<<< orphan*/  ULP_RX_LA_CTL_A ; 
 int /*<<< orphan*/  ULP_RX_LA_RDDATA_A ; 
 int /*<<< orphan*/  ULP_RX_LA_RDPTR_A ; 
 int /*<<< orphan*/  ULP_RX_LA_WRPTR_A ; 
 void* t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

void t4_ulprx_read_la(struct adapter *adap, u32 *la_buf)
{
	unsigned int i, j;

	for (i = 0; i < 8; i++) {
		u32 *p = la_buf + i;

		t4_write_reg(adap, ULP_RX_LA_CTL_A, i);
		j = t4_read_reg(adap, ULP_RX_LA_WRPTR_A);
		t4_write_reg(adap, ULP_RX_LA_RDPTR_A, j);
		for (j = 0; j < ULPRX_LA_SIZE; j++, p += 8)
			*p = t4_read_reg(adap, ULP_RX_LA_RDDATA_A);
	}
}