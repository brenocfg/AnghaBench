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
struct crypto_tfm {int dummy; } ;
struct crypto_instance {int dummy; } ;
struct cryptd_queue {int dummy; } ;
struct cryptd_instance_ctx {struct cryptd_queue* queue; } ;

/* Variables and functions */
 struct cryptd_instance_ctx* crypto_instance_ctx (struct crypto_instance*) ; 
 struct crypto_instance* crypto_tfm_alg_instance (struct crypto_tfm*) ; 

__attribute__((used)) static inline struct cryptd_queue *cryptd_get_queue(struct crypto_tfm *tfm)
{
	struct crypto_instance *inst = crypto_tfm_alg_instance(tfm);
	struct cryptd_instance_ctx *ictx = crypto_instance_ctx(inst);
	return ictx->queue;
}