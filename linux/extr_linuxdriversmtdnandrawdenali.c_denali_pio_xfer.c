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
struct denali_nand_info {int dummy; } ;

/* Variables and functions */
 int denali_pio_read (struct denali_nand_info*,void*,size_t,int,int) ; 
 int denali_pio_write (struct denali_nand_info*,void*,size_t,int,int) ; 

__attribute__((used)) static int denali_pio_xfer(struct denali_nand_info *denali, void *buf,
			   size_t size, int page, int raw, int write)
{
	if (write)
		return denali_pio_write(denali, buf, size, page, raw);
	else
		return denali_pio_read(denali, buf, size, page, raw);
}