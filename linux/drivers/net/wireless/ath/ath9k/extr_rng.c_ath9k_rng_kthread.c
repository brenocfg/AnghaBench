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
typedef  scalar_t__ u32 ;
struct ath_softc {int /*<<< orphan*/ * rng_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_RNG_BUF_SIZE ; 
 int /*<<< orphan*/  ATH9K_RNG_ENTROPY (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_hwgenerator_randomness (void*,int,int /*<<< orphan*/ ) ; 
 int ath9k_rng_data_read (struct ath_softc*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath9k_rng_delay_get (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  rng_queue ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_rng_kthread(void *data)
{
	int bytes_read;
	struct ath_softc *sc = data;
	u32 *rng_buf;
	u32 delay, fail_stats = 0;

	rng_buf = kmalloc_array(ATH9K_RNG_BUF_SIZE, sizeof(u32), GFP_KERNEL);
	if (!rng_buf)
		goto out;

	while (!kthread_should_stop()) {
		bytes_read = ath9k_rng_data_read(sc, rng_buf,
						 ATH9K_RNG_BUF_SIZE);
		if (unlikely(!bytes_read)) {
			delay = ath9k_rng_delay_get(++fail_stats);
			wait_event_interruptible_timeout(rng_queue,
							 kthread_should_stop(),
							 msecs_to_jiffies(delay));
			continue;
		}

		fail_stats = 0;

		/* sleep until entropy bits under write_wakeup_threshold */
		add_hwgenerator_randomness((void *)rng_buf, bytes_read,
					   ATH9K_RNG_ENTROPY(bytes_read));
	}

	kfree(rng_buf);
out:
	sc->rng_task = NULL;

	return 0;
}