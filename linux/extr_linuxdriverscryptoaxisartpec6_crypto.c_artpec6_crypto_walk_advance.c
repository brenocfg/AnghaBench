#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct artpec6_crypto_walk {scalar_t__ offset; TYPE_1__* sg; } ;
struct TYPE_3__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 size_t min (size_t,scalar_t__) ; 
 TYPE_1__* sg_next (TYPE_1__*) ; 

__attribute__((used)) static size_t artpec6_crypto_walk_advance(struct artpec6_crypto_walk *awalk,
					  size_t nbytes)
{
	while (nbytes && awalk->sg) {
		size_t piece;

		WARN_ON(awalk->offset > awalk->sg->length);

		piece = min(nbytes, (size_t)awalk->sg->length - awalk->offset);
		nbytes -= piece;
		awalk->offset += piece;
		if (awalk->offset == awalk->sg->length) {
			awalk->sg = sg_next(awalk->sg);
			awalk->offset = 0;
		}

	}

	return nbytes;
}