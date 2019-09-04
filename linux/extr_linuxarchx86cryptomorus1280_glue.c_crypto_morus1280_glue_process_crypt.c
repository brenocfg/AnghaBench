#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {TYPE_4__ virt; } ;
struct skcipher_walk {int nbytes; TYPE_2__ dst; TYPE_3__ src; } ;
struct morus1280_state {int dummy; } ;
struct morus1280_ops {int /*<<< orphan*/  (* crypt_tail ) (struct morus1280_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* crypt_blocks ) (struct morus1280_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MORUS1280_BLOCK_SIZE ; 
 int /*<<< orphan*/  round_down (int,int) ; 
 int /*<<< orphan*/  skcipher_walk_done (struct skcipher_walk*,int) ; 
 int /*<<< orphan*/  stub1 (struct morus1280_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct morus1280_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void crypto_morus1280_glue_process_crypt(struct morus1280_state *state,
						struct morus1280_ops ops,
						struct skcipher_walk *walk)
{
	while (walk->nbytes >= MORUS1280_BLOCK_SIZE) {
		ops.crypt_blocks(state, walk->src.virt.addr,
				 walk->dst.virt.addr,
				 round_down(walk->nbytes,
					    MORUS1280_BLOCK_SIZE));
		skcipher_walk_done(walk, walk->nbytes % MORUS1280_BLOCK_SIZE);
	}

	if (walk->nbytes) {
		ops.crypt_tail(state, walk->src.virt.addr, walk->dst.virt.addr,
			       walk->nbytes);
		skcipher_walk_done(walk, 0);
	}
}