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
struct hnae3_client {int type; } ;
struct hnae3_ae_dev {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
#define  HNAE3_CLIENT_KNIC 129 
#define  HNAE3_CLIENT_ROCE 128 
 int /*<<< orphan*/  HNAE3_KNIC_CLIENT_INITED_B ; 
 int /*<<< orphan*/  HNAE3_ROCE_CLIENT_INITED_B ; 
 int hnae3_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hnae3_get_client_init_flag(struct hnae3_client *client,
				      struct hnae3_ae_dev *ae_dev)
{
	int inited = 0;

	switch (client->type) {
	case HNAE3_CLIENT_KNIC:
		inited = hnae3_get_bit(ae_dev->flag,
				       HNAE3_KNIC_CLIENT_INITED_B);
		break;
	case HNAE3_CLIENT_ROCE:
		inited = hnae3_get_bit(ae_dev->flag,
				       HNAE3_ROCE_CLIENT_INITED_B);
		break;
	default:
		break;
	}

	return inited;
}