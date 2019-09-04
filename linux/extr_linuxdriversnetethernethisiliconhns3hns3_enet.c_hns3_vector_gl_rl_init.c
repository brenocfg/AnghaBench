#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hns3_nic_priv {struct hnae3_handle* ae_handle; } ;
struct TYPE_9__ {int gl_adapt_enable; void* flow_level; void* int_gl; } ;
struct TYPE_10__ {TYPE_4__ coal; } ;
struct TYPE_7__ {int gl_adapt_enable; void* flow_level; void* int_gl; } ;
struct TYPE_8__ {TYPE_2__ coal; } ;
struct hns3_enet_tqp_vector {TYPE_5__ tx_group; TYPE_3__ rx_group; int /*<<< orphan*/  int_adapt_down; } ;
struct TYPE_6__ {scalar_t__ int_rl_setting; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;

/* Variables and functions */
 void* HNS3_FLOW_LOW ; 
 int /*<<< orphan*/  HNS3_INT_ADAPT_DOWN_START ; 
 void* HNS3_INT_GL_50K ; 

__attribute__((used)) static void hns3_vector_gl_rl_init(struct hns3_enet_tqp_vector *tqp_vector,
				   struct hns3_nic_priv *priv)
{
	struct hnae3_handle *h = priv->ae_handle;

	/* initialize the configuration for interrupt coalescing.
	 * 1. GL (Interrupt Gap Limiter)
	 * 2. RL (Interrupt Rate Limiter)
	 */

	/* Default: enable interrupt coalescing self-adaptive and GL */
	tqp_vector->tx_group.coal.gl_adapt_enable = 1;
	tqp_vector->rx_group.coal.gl_adapt_enable = 1;

	tqp_vector->tx_group.coal.int_gl = HNS3_INT_GL_50K;
	tqp_vector->rx_group.coal.int_gl = HNS3_INT_GL_50K;

	/* Default: disable RL */
	h->kinfo.int_rl_setting = 0;

	tqp_vector->int_adapt_down = HNS3_INT_ADAPT_DOWN_START;
	tqp_vector->rx_group.coal.flow_level = HNS3_FLOW_LOW;
	tqp_vector->tx_group.coal.flow_level = HNS3_FLOW_LOW;
}