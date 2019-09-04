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
struct hnae3_ae_dev {TYPE_2__* ops; TYPE_1__* pdev; int /*<<< orphan*/  flag; int /*<<< orphan*/  dev_type; } ;
struct TYPE_4__ {int (* init_client_instance ) (struct hnae3_client*,struct hnae3_ae_dev*) ;int /*<<< orphan*/  (* uninit_client_instance ) (struct hnae3_client*,struct hnae3_ae_dev*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_DEV_INITED_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ hnae3_client_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hnae3_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hnae3_get_client_init_flag (struct hnae3_client*,struct hnae3_ae_dev*) ; 
 int /*<<< orphan*/  hnae3_set_client_init_flag (struct hnae3_client*,struct hnae3_ae_dev*,int) ; 
 int stub1 (struct hnae3_client*,struct hnae3_ae_dev*) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_client*,struct hnae3_ae_dev*) ; 

__attribute__((used)) static int hnae3_match_n_instantiate(struct hnae3_client *client,
				     struct hnae3_ae_dev *ae_dev, bool is_reg)
{
	int ret;

	/* check if this client matches the type of ae_dev */
	if (!(hnae3_client_match(client->type, ae_dev->dev_type) &&
	      hnae3_get_bit(ae_dev->flag, HNAE3_DEV_INITED_B))) {
		return 0;
	}

	/* now, (un-)instantiate client by calling lower layer */
	if (is_reg) {
		ret = ae_dev->ops->init_client_instance(client, ae_dev);
		if (ret) {
			dev_err(&ae_dev->pdev->dev,
				"fail to instantiate client, ret = %d\n", ret);
			return ret;
		}

		hnae3_set_client_init_flag(client, ae_dev, 1);
		return 0;
	}

	if (hnae3_get_client_init_flag(client, ae_dev)) {
		ae_dev->ops->uninit_client_instance(client, ae_dev);

		hnae3_set_client_init_flag(client, ae_dev, 0);
	}

	return 0;
}