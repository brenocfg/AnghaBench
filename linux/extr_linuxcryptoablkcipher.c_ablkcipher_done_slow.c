#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sg; } ;
struct ablkcipher_walk {TYPE_1__ out; } ;

/* Variables and functions */
 int /*<<< orphan*/  scatterwalk_advance (TYPE_1__*,unsigned int) ; 
 unsigned int scatterwalk_pagelen (TYPE_1__*) ; 
 int /*<<< orphan*/  scatterwalk_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ablkcipher_done_slow(struct ablkcipher_walk *walk,
					unsigned int n)
{
	for (;;) {
		unsigned int len_this_page = scatterwalk_pagelen(&walk->out);

		if (len_this_page > n)
			len_this_page = n;
		scatterwalk_advance(&walk->out, n);
		if (n == len_this_page)
			break;
		n -= len_this_page;
		scatterwalk_start(&walk->out, sg_next(walk->out.sg));
	}
}