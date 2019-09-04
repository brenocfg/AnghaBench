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
struct mtk_aes_rec {int /*<<< orphan*/  id; int /*<<< orphan*/  cryp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_aes_handle_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_aes_queue_task(unsigned long data)
{
	struct mtk_aes_rec *aes = (struct mtk_aes_rec *)data;

	mtk_aes_handle_queue(aes->cryp, aes->id, NULL);
}