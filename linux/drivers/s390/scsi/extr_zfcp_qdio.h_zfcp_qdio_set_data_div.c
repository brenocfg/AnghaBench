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
typedef  int /*<<< orphan*/  u32 ;
struct zfcp_qdio_req {size_t sbal_first; } ;
struct zfcp_qdio {TYPE_1__** req_q; } ;
struct qdio_buffer_element {int /*<<< orphan*/  length; } ;
struct TYPE_2__ {struct qdio_buffer_element* element; } ;

/* Variables and functions */

__attribute__((used)) static inline
void zfcp_qdio_set_data_div(struct zfcp_qdio *qdio,
			    struct zfcp_qdio_req *q_req, u32 count)
{
	struct qdio_buffer_element *sbale;

	sbale = qdio->req_q[q_req->sbal_first]->element;
	sbale->length = count;
}