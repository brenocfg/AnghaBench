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
struct device {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct ablkcipher_edesc {int /*<<< orphan*/  sec4_sg_bytes; int /*<<< orphan*/  sec4_sg_dma; int /*<<< orphan*/  iv_dir; int /*<<< orphan*/  iv_dma; int /*<<< orphan*/  dst_nents; int /*<<< orphan*/  src_nents; } ;

/* Variables and functions */
 int /*<<< orphan*/  caam_unmap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 

__attribute__((used)) static void ablkcipher_unmap(struct device *dev,
			     struct ablkcipher_edesc *edesc,
			     struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *ablkcipher = crypto_ablkcipher_reqtfm(req);
	int ivsize = crypto_ablkcipher_ivsize(ablkcipher);

	caam_unmap(dev, req->src, req->dst,
		   edesc->src_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize, edesc->iv_dir,
		   edesc->sec4_sg_dma, edesc->sec4_sg_bytes);
}