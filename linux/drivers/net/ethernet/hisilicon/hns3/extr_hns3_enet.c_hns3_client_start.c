#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* client_start ) (struct hnae3_handle*) ;} ;

/* Variables and functions */
 int stub1 (struct hnae3_handle*) ; 

__attribute__((used)) static int hns3_client_start(struct hnae3_handle *handle)
{
	if (!handle->ae_algo->ops->client_start)
		return 0;

	return handle->ae_algo->ops->client_start(handle);
}