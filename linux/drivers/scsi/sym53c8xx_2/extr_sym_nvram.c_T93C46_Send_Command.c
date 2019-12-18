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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct sym_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INB (struct sym_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T93C46_Write_Bit (struct sym_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nc_gpreg ; 

__attribute__((used)) static void T93C46_Send_Command(struct sym_device *np, u_short write_data, 
				u_char *read_bit, u_char *gpreg)
{
	int x;

	/* send 9 bits, start bit (1), command (2), address (6)  */
	for (x = 0; x < 9; x++)
		T93C46_Write_Bit(np, (u_char) (write_data >> (8 - x)), gpreg);

	*read_bit = INB(np, nc_gpreg);
}