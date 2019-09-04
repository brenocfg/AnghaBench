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
struct skcipher_walk {int /*<<< orphan*/  buffers; int /*<<< orphan*/  flags; } ;
struct skcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SKCIPHER_WALK_PHYS ; 
 int skcipher_walk_skcipher (struct skcipher_walk*,struct skcipher_request*) ; 

int skcipher_walk_async(struct skcipher_walk *walk,
			struct skcipher_request *req)
{
	walk->flags |= SKCIPHER_WALK_PHYS;

	INIT_LIST_HEAD(&walk->buffers);

	return skcipher_walk_skcipher(walk, req);
}