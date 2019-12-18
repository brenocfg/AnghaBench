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
struct ucsi_ccg {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  CCGX_RAB_INTR_REG ; 
 int ccg_read (struct ucsi_ccg*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int ccg_write (struct ucsi_ccg*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int ucsi_ccg_ack_interrupt(struct ucsi_ccg *uc)
{
	int status;
	unsigned char data;

	status = ccg_read(uc, CCGX_RAB_INTR_REG, &data, sizeof(data));
	if (status < 0)
		return status;

	return ccg_write(uc, CCGX_RAB_INTR_REG, &data, sizeof(data));
}