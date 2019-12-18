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
struct TYPE_2__ {int /*<<< orphan*/  transfer_len; int /*<<< orphan*/  sg; } ;
struct nvmet_tcp_cmd {TYPE_1__ req; int /*<<< orphan*/  exp_ddgst; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_digest (struct ahash_request*) ; 

__attribute__((used)) static void nvmet_tcp_ddgst(struct ahash_request *hash,
		struct nvmet_tcp_cmd *cmd)
{
	ahash_request_set_crypt(hash, cmd->req.sg,
		(void *)&cmd->exp_ddgst, cmd->req.transfer_len);
	crypto_ahash_digest(hash);
}