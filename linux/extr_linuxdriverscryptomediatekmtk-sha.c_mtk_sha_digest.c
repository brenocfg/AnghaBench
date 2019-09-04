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
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int mtk_sha_finup (struct ahash_request*) ; 
 scalar_t__ mtk_sha_init (struct ahash_request*) ; 

__attribute__((used)) static int mtk_sha_digest(struct ahash_request *req)
{
	return mtk_sha_init(req) ?: mtk_sha_finup(req);
}