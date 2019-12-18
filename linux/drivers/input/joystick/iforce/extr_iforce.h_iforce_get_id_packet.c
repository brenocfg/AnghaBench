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
typedef  int /*<<< orphan*/  u8 ;
struct iforce {TYPE_1__* xport_ops; } ;
struct TYPE_2__ {int (* get_id ) (struct iforce*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ;} ;

/* Variables and functions */
 int stub1 (struct iforce*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static inline int iforce_get_id_packet(struct iforce *iforce, u8 id,
				       u8 *response_data, size_t *response_len)
{
	return iforce->xport_ops->get_id(iforce, id,
					 response_data, response_len);
}