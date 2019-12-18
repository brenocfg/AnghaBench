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
struct hnae3_client {int /*<<< orphan*/  type; } ;
struct hnae3_ae_dev {TYPE_1__* ops; int /*<<< orphan*/  flag; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* uninit_client_instance ) (struct hnae3_client*,struct hnae3_ae_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_DEV_INITED_B ; 
 scalar_t__ hnae3_client_match (int /*<<< orphan*/ ) ; 
 scalar_t__ hnae3_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hnae3_get_client_init_flag (struct hnae3_client*,struct hnae3_ae_dev*) ; 
 int /*<<< orphan*/  hnae3_set_client_init_flag (struct hnae3_client*,struct hnae3_ae_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_client*,struct hnae3_ae_dev*) ; 

__attribute__((used)) static void hnae3_uninit_client_instance(struct hnae3_client *client,
					 struct hnae3_ae_dev *ae_dev)
{
	/* check if this client matches the type of ae_dev */
	if (!(hnae3_client_match(client->type) &&
	      hnae3_get_bit(ae_dev->flag, HNAE3_DEV_INITED_B)))
		return;

	if (hnae3_get_client_init_flag(client, ae_dev)) {
		ae_dev->ops->uninit_client_instance(client, ae_dev);

		hnae3_set_client_init_flag(client, ae_dev, 0);
	}
}