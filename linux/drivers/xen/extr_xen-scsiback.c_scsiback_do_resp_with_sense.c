#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vscsibk_pend {TYPE_1__* v2p; int /*<<< orphan*/  rqid; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsiback_free_translation_entry ; 
 int /*<<< orphan*/  scsiback_send_response (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsiback_do_resp_with_sense(char *sense_buffer, int32_t result,
			uint32_t resid, struct vscsibk_pend *pending_req)
{
	scsiback_send_response(pending_req->info, sense_buffer, result,
			       resid, pending_req->rqid);

	if (pending_req->v2p)
		kref_put(&pending_req->v2p->kref,
			 scsiback_free_translation_entry);
}