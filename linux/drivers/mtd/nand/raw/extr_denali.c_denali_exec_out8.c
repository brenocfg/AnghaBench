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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct denali_controller {int /*<<< orphan*/  (* host_write ) (struct denali_controller*,int,int /*<<< orphan*/  const) ;} ;

/* Variables and functions */
 int DENALI_BANK (struct denali_controller*) ; 
 int /*<<< orphan*/  stub1 (struct denali_controller*,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void denali_exec_out8(struct denali_controller *denali, u32 type,
			     const u8 *buf, unsigned int len)
{
	int i;

	for (i = 0; i < len; i++)
		denali->host_write(denali, type | DENALI_BANK(denali), buf[i]);
}