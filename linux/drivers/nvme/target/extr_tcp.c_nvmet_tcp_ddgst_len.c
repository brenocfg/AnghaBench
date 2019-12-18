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
typedef  int /*<<< orphan*/  u8 ;
struct nvmet_tcp_queue {scalar_t__ data_digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_TCP_DIGEST_LENGTH ; 

__attribute__((used)) static inline u8 nvmet_tcp_ddgst_len(struct nvmet_tcp_queue *queue)
{
	return queue->data_digest ? NVME_TCP_DIGEST_LENGTH : 0;
}