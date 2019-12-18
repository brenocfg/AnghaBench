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
struct zfcp_qdio_req {size_t sbal_last; } ;
struct zfcp_qdio {TYPE_1__** req_q; } ;
struct qdio_buffer_element {int dummy; } ;
struct TYPE_2__ {struct qdio_buffer_element* element; } ;

/* Variables and functions */

__attribute__((used)) static inline struct qdio_buffer_element *
zfcp_qdio_sbale_req(struct zfcp_qdio *qdio, struct zfcp_qdio_req *q_req)
{
	return &qdio->req_q[q_req->sbal_last]->element[0];
}