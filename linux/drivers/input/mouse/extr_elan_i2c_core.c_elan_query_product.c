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
struct elan_tp_data {int /*<<< orphan*/  clickpad; int /*<<< orphan*/  sm_version; int /*<<< orphan*/  ic_type; int /*<<< orphan*/  client; TYPE_1__* ops; int /*<<< orphan*/  product_id; } ;
struct TYPE_2__ {int (* get_product_id ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* get_sm_version ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elan_query_product(struct elan_tp_data *data)
{
	int error;

	error = data->ops->get_product_id(data->client, &data->product_id);
	if (error)
		return error;

	error = data->ops->get_sm_version(data->client, &data->ic_type,
					  &data->sm_version, &data->clickpad);
	if (error)
		return error;

	return 0;
}