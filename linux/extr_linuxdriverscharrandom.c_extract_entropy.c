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
struct entropy_store {int last_data_init; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; int /*<<< orphan*/  last_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ENTROPY_BITS (struct entropy_store*) ; 
 int EXTRACT_SIZE ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  _extract_entropy (struct entropy_store*,void*,size_t,scalar_t__) ; 
 size_t account (struct entropy_store*,size_t,int,int) ; 
 int /*<<< orphan*/  extract_buf (struct entropy_store*,int /*<<< orphan*/ *) ; 
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_extract_entropy (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfer_secondary_pool (struct entropy_store*,size_t) ; 

__attribute__((used)) static ssize_t extract_entropy(struct entropy_store *r, void *buf,
				 size_t nbytes, int min, int reserved)
{
	__u8 tmp[EXTRACT_SIZE];
	unsigned long flags;

	/* if last_data isn't primed, we need EXTRACT_SIZE extra bytes */
	if (fips_enabled) {
		spin_lock_irqsave(&r->lock, flags);
		if (!r->last_data_init) {
			r->last_data_init = 1;
			spin_unlock_irqrestore(&r->lock, flags);
			trace_extract_entropy(r->name, EXTRACT_SIZE,
					      ENTROPY_BITS(r), _RET_IP_);
			xfer_secondary_pool(r, EXTRACT_SIZE);
			extract_buf(r, tmp);
			spin_lock_irqsave(&r->lock, flags);
			memcpy(r->last_data, tmp, EXTRACT_SIZE);
		}
		spin_unlock_irqrestore(&r->lock, flags);
	}

	trace_extract_entropy(r->name, nbytes, ENTROPY_BITS(r), _RET_IP_);
	xfer_secondary_pool(r, nbytes);
	nbytes = account(r, nbytes, min, reserved);

	return _extract_entropy(r, buf, nbytes, fips_enabled);
}