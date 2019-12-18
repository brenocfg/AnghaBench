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
typedef  int /*<<< orphan*/  u32 ;
struct nvmet_req {TYPE_2__* cqe; } ;
struct TYPE_3__ {int /*<<< orphan*/  u32; } ;
struct TYPE_4__ {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nvmet_set_result(struct nvmet_req *req, u32 result)
{
	req->cqe->result.u32 = cpu_to_le32(result);
}