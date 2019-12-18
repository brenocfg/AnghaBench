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
struct dm_integrity_c {unsigned int log2_buffer_sectors; int /*<<< orphan*/  bufio; } ;
struct dm_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (unsigned char*) ; 
 int PTR_ERR (unsigned char*) ; 
 unsigned int SECTOR_SHIFT ; 
 int TAG_READ ; 
 int TAG_WRITE ; 
 int /*<<< orphan*/  dm_bufio_mark_partial_buffer_dirty (struct dm_buffer*,unsigned int,unsigned int) ; 
 unsigned char* dm_bufio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_buffer**) ; 
 int /*<<< orphan*/  dm_bufio_release (struct dm_buffer*) ; 
 int dm_integrity_failed (struct dm_integrity_c*) ; 
 int memcmp (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dm_integrity_rw_tag(struct dm_integrity_c *ic, unsigned char *tag, sector_t *metadata_block,
			       unsigned *metadata_offset, unsigned total_size, int op)
{
	do {
		unsigned char *data, *dp;
		struct dm_buffer *b;
		unsigned to_copy;
		int r;

		r = dm_integrity_failed(ic);
		if (unlikely(r))
			return r;

		data = dm_bufio_read(ic->bufio, *metadata_block, &b);
		if (IS_ERR(data))
			return PTR_ERR(data);

		to_copy = min((1U << SECTOR_SHIFT << ic->log2_buffer_sectors) - *metadata_offset, total_size);
		dp = data + *metadata_offset;
		if (op == TAG_READ) {
			memcpy(tag, dp, to_copy);
		} else if (op == TAG_WRITE) {
			memcpy(dp, tag, to_copy);
			dm_bufio_mark_partial_buffer_dirty(b, *metadata_offset, *metadata_offset + to_copy);
		} else  {
			/* e.g.: op == TAG_CMP */
			if (unlikely(memcmp(dp, tag, to_copy))) {
				unsigned i;

				for (i = 0; i < to_copy; i++) {
					if (dp[i] != tag[i])
						break;
					total_size--;
				}
				dm_bufio_release(b);
				return total_size;
			}
		}
		dm_bufio_release(b);

		tag += to_copy;
		*metadata_offset += to_copy;
		if (unlikely(*metadata_offset == 1U << SECTOR_SHIFT << ic->log2_buffer_sectors)) {
			(*metadata_block)++;
			*metadata_offset = 0;
		}
		total_size -= to_copy;
	} while (unlikely(total_size));

	return 0;
}