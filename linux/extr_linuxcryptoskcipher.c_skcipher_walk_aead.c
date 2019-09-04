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
struct skcipher_walk {int /*<<< orphan*/  total; } ;
struct aead_request {int /*<<< orphan*/  cryptlen; } ;

/* Variables and functions */
 int skcipher_walk_aead_common (struct skcipher_walk*,struct aead_request*,int) ; 

int skcipher_walk_aead(struct skcipher_walk *walk, struct aead_request *req,
		       bool atomic)
{
	walk->total = req->cryptlen;

	return skcipher_walk_aead_common(walk, req, atomic);
}