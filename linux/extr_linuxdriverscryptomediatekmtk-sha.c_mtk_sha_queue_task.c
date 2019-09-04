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
struct mtk_sha_rec {scalar_t__ id; int /*<<< orphan*/  cryp; } ;

/* Variables and functions */
 scalar_t__ MTK_RING2 ; 
 int /*<<< orphan*/  mtk_sha_handle_queue (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_sha_queue_task(unsigned long data)
{
	struct mtk_sha_rec *sha = (struct mtk_sha_rec *)data;

	mtk_sha_handle_queue(sha->cryp, sha->id - MTK_RING2, NULL);
}