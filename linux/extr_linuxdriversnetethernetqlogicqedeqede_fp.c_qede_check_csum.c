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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  qede_check_notunn_csum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_check_tunn_csum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_tunn_exist (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 qede_check_csum(u16 flag)
{
	if (!qede_tunn_exist(flag))
		return qede_check_notunn_csum(flag);
	else
		return qede_check_tunn_csum(flag);
}