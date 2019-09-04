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
struct mtk_cryp {int dummy; } ;
struct mtk_aes_rec {int /*<<< orphan*/  (* resume ) (struct mtk_cryp*,struct mtk_aes_rec*) ;struct mtk_cryp* cryp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_aes_unmap (struct mtk_cryp*,struct mtk_aes_rec*) ; 
 int /*<<< orphan*/  stub1 (struct mtk_cryp*,struct mtk_aes_rec*) ; 

__attribute__((used)) static void mtk_aes_done_task(unsigned long data)
{
	struct mtk_aes_rec *aes = (struct mtk_aes_rec *)data;
	struct mtk_cryp *cryp = aes->cryp;

	mtk_aes_unmap(cryp, aes);
	aes->resume(cryp, aes);
}