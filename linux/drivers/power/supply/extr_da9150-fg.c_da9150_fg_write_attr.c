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
typedef  int u32 ;
struct da9150_fg {int /*<<< orphan*/  da9150; } ;

/* Variables and functions */
 int DA9150_QIF_BYTE_MASK ; 
 int DA9150_QIF_BYTE_SIZE ; 
 int DA9150_QIF_CODE_MASK ; 
 int DA9150_QIF_LONG_SIZE ; 
 int DA9150_QIF_WRITE ; 
 int /*<<< orphan*/  da9150_write_qif (int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static void da9150_fg_write_attr(struct da9150_fg *fg, u8 code, u8 size,
				 u32 val)

{
	u8 buf[DA9150_QIF_LONG_SIZE];
	u8 write_addr;
	int i;

	/* Set QIF code (WRITE mode) */
	write_addr = (code & DA9150_QIF_CODE_MASK) | DA9150_QIF_WRITE;

	for (i = 0; i < size; ++i) {
		buf[i] = (val >> (i * DA9150_QIF_BYTE_SIZE)) &
			 DA9150_QIF_BYTE_MASK;
	}
	da9150_write_qif(fg->da9150, write_addr, size, buf);
}