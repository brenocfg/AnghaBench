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
typedef  int u32 ;
struct kfifo {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RANDOM_SIZE ; 
 scalar_t__ kfifo_alloc (struct kfifo*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_in (struct kfifo*,unsigned char*,int) ; 
 int kfifo_out_locked (struct kfifo*,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int prandom_u32 () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __cxio_init_resource_fifo(struct kfifo *fifo,
				   spinlock_t *fifo_lock,
				   u32 nr, u32 skip_low,
				   u32 skip_high,
				   int random)
{
	u32 i, j, entry = 0, idx;
	u32 random_bytes;
	u32 rarray[16];
	spin_lock_init(fifo_lock);

	if (kfifo_alloc(fifo, nr * sizeof(u32), GFP_KERNEL))
		return -ENOMEM;

	for (i = 0; i < skip_low + skip_high; i++)
		kfifo_in(fifo, (unsigned char *) &entry, sizeof(u32));
	if (random) {
		j = 0;
		random_bytes = prandom_u32();
		for (i = 0; i < RANDOM_SIZE; i++)
			rarray[i] = i + skip_low;
		for (i = skip_low + RANDOM_SIZE; i < nr - skip_high; i++) {
			if (j >= RANDOM_SIZE) {
				j = 0;
				random_bytes = prandom_u32();
			}
			idx = (random_bytes >> (j * 2)) & 0xF;
			kfifo_in(fifo,
				(unsigned char *) &rarray[idx],
				sizeof(u32));
			rarray[idx] = i;
			j++;
		}
		for (i = 0; i < RANDOM_SIZE; i++)
			kfifo_in(fifo,
				(unsigned char *) &rarray[i],
				sizeof(u32));
	} else
		for (i = skip_low; i < nr - skip_high; i++)
			kfifo_in(fifo, (unsigned char *) &i, sizeof(u32));

	for (i = 0; i < skip_low + skip_high; i++)
		if (kfifo_out_locked(fifo, (unsigned char *) &entry,
				sizeof(u32), fifo_lock) != sizeof(u32))
					break;
	return 0;
}