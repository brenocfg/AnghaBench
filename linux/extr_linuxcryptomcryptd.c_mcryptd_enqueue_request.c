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
struct mcryptd_queue {int /*<<< orphan*/  cpu_queue; } ;
struct TYPE_2__ {void* cpu; } ;
struct mcryptd_hash_request_ctx {TYPE_1__ tag; } ;
struct mcryptd_cpu_queue {int /*<<< orphan*/  work; int /*<<< orphan*/  q_lock; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 int /*<<< orphan*/  kcrypto_wq ; 
 int /*<<< orphan*/  pr_debug (char*,int,struct mcryptd_cpu_queue*,struct crypto_async_request*) ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mcryptd_cpu_queue* raw_cpu_ptr (int /*<<< orphan*/ ) ; 
 void* smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcryptd_enqueue_request(struct mcryptd_queue *queue,
				  struct crypto_async_request *request,
				  struct mcryptd_hash_request_ctx *rctx)
{
	int cpu, err;
	struct mcryptd_cpu_queue *cpu_queue;

	cpu_queue = raw_cpu_ptr(queue->cpu_queue);
	spin_lock(&cpu_queue->q_lock);
	cpu = smp_processor_id();
	rctx->tag.cpu = smp_processor_id();

	err = crypto_enqueue_request(&cpu_queue->queue, request);
	pr_debug("enqueue request: cpu %d cpu_queue %p request %p\n",
		 cpu, cpu_queue, request);
	spin_unlock(&cpu_queue->q_lock);
	queue_work_on(cpu, kcrypto_wq, &cpu_queue->work);

	return err;
}