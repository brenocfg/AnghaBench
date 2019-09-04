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
struct mtk_aes_rec {int dummy; } ;

/* Variables and functions */
 int mtk_aes_complete (struct mtk_cryp*,struct mtk_aes_rec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_aes_transfer_complete(struct mtk_cryp *cryp,
				     struct mtk_aes_rec *aes)
{
	return mtk_aes_complete(cryp, aes, 0);
}