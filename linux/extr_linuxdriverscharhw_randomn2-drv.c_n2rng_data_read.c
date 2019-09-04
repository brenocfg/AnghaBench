#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct n2rng {int test_data; int flags; int buffer; int /*<<< orphan*/  work; TYPE_1__* op; } ;
struct hwrng {scalar_t__ priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int N2RNG_FLAG_BUFFER_VALID ; 
 int N2RNG_FLAG_READY ; 
 int N2RNG_FLAG_SHUTDOWN ; 
 unsigned long __pa (int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int n2rng_generic_read_data (unsigned long) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int n2rng_data_read(struct hwrng *rng, u32 *data)
{
	struct n2rng *np = (struct n2rng *) rng->priv;
	unsigned long ra = __pa(&np->test_data);
	int len;

	if (!(np->flags & N2RNG_FLAG_READY)) {
		len = 0;
	} else if (np->flags & N2RNG_FLAG_BUFFER_VALID) {
		np->flags &= ~N2RNG_FLAG_BUFFER_VALID;
		*data = np->buffer;
		len = 4;
	} else {
		int err = n2rng_generic_read_data(ra);
		if (!err) {
			np->flags |= N2RNG_FLAG_BUFFER_VALID;
			np->buffer = np->test_data >> 32;
			*data = np->test_data & 0xffffffff;
			len = 4;
		} else {
			dev_err(&np->op->dev, "RNG error, retesting\n");
			np->flags &= ~N2RNG_FLAG_READY;
			if (!(np->flags & N2RNG_FLAG_SHUTDOWN))
				schedule_delayed_work(&np->work, 0);
			len = 0;
		}
	}

	return len;
}