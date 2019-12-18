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
struct smm_eps_table {int /*<<< orphan*/  length; int /*<<< orphan*/  smm_comm_buff_anchor; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMM_EPS_SIG ; 
 scalar_t__ checksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct smm_eps_table *check_eps_table(u8 *addr)
{
	struct smm_eps_table *eps = (struct smm_eps_table *)addr;

	if (strncmp(eps->smm_comm_buff_anchor, SMM_EPS_SIG, 4) != 0)
		return NULL;

	if (checksum(addr, eps->length) != 0)
		return NULL;

	return eps;
}