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
struct ccp_data {int /*<<< orphan*/  sg_wa; int /*<<< orphan*/  dm_wa; } ;
struct ccp_cmd_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccp_dm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccp_sg_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccp_free_data(struct ccp_data *data, struct ccp_cmd_queue *cmd_q)
{
	ccp_dm_free(&data->dm_wa);
	ccp_sg_free(&data->sg_wa);
}