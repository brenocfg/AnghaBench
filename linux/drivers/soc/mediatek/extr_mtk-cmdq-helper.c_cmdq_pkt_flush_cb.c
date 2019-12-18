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
struct cmdq_flush_completion {int err; int /*<<< orphan*/  cmplt; } ;
struct cmdq_cb_data {scalar_t__ sta; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ CMDQ_CB_NORMAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmdq_pkt_flush_cb(struct cmdq_cb_data data)
{
	struct cmdq_flush_completion *cmplt;

	cmplt = (struct cmdq_flush_completion *)data.data;
	if (data.sta != CMDQ_CB_NORMAL)
		cmplt->err = true;
	else
		cmplt->err = false;
	complete(&cmplt->cmplt);
}