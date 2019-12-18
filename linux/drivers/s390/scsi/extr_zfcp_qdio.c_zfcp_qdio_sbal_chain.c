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
struct zfcp_qdio_req {scalar_t__ sbal_number; int /*<<< orphan*/  sbtype; scalar_t__ sbale_curr; int /*<<< orphan*/  sbal_last; int /*<<< orphan*/  sbal_limit; } ;
struct zfcp_qdio {int dummy; } ;
struct qdio_buffer_element {int /*<<< orphan*/  sflags; int /*<<< orphan*/  eflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  SBAL_EFLAGS_LAST_ENTRY ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_MORE_SBALS ; 
 scalar_t__ ZFCP_QDIO_MAX_SBALS_PER_REQ ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_curr (struct zfcp_qdio*,struct zfcp_qdio_req*) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_req (struct zfcp_qdio*,struct zfcp_qdio_req*) ; 

__attribute__((used)) static struct qdio_buffer_element *
zfcp_qdio_sbal_chain(struct zfcp_qdio *qdio, struct zfcp_qdio_req *q_req)
{
	struct qdio_buffer_element *sbale;

	/* set last entry flag in current SBALE of current SBAL */
	sbale = zfcp_qdio_sbale_curr(qdio, q_req);
	sbale->eflags |= SBAL_EFLAGS_LAST_ENTRY;

	/* don't exceed last allowed SBAL */
	if (q_req->sbal_last == q_req->sbal_limit)
		return NULL;

	/* set chaining flag in first SBALE of current SBAL */
	sbale = zfcp_qdio_sbale_req(qdio, q_req);
	sbale->sflags |= SBAL_SFLAGS0_MORE_SBALS;

	/* calculate index of next SBAL */
	q_req->sbal_last++;
	q_req->sbal_last %= QDIO_MAX_BUFFERS_PER_Q;

	/* keep this requests number of SBALs up-to-date */
	q_req->sbal_number++;
	BUG_ON(q_req->sbal_number > ZFCP_QDIO_MAX_SBALS_PER_REQ);

	/* start at first SBALE of new SBAL */
	q_req->sbale_curr = 0;

	/* set storage-block type for new SBAL */
	sbale = zfcp_qdio_sbale_curr(qdio, q_req);
	sbale->sflags |= q_req->sbtype;

	return sbale;
}