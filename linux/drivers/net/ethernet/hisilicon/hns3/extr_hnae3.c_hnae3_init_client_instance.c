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
struct hnae3_client {int /*<<< orphan*/  type; } ;
struct hnae3_ae_dev {TYPE_2__* pdev; TYPE_1__* ops; int /*<<< orphan*/  flag; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* init_client_instance ) (struct hnae3_client*,struct hnae3_ae_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_DEV_INITED_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ hnae3_client_match (int /*<<< orphan*/ ) ; 
 scalar_t__ hnae3_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct hnae3_client*,struct hnae3_ae_dev*) ; 

__attribute__((used)) static int hnae3_init_client_instance(struct hnae3_client *client,
				      struct hnae3_ae_dev *ae_dev)
{
	int ret;

	/* check if this client matches the type of ae_dev */
	if (!(hnae3_client_match(client->type) &&
	      hnae3_get_bit(ae_dev->flag, HNAE3_DEV_INITED_B))) {
		return 0;
	}

	ret = ae_dev->ops->init_client_instance(client, ae_dev);
	if (ret)
		dev_err(&ae_dev->pdev->dev,
			"fail to instantiate client, ret = %d\n", ret);

	return ret;
}