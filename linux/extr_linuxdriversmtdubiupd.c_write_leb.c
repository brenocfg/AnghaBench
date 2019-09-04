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
struct ubi_volume {scalar_t__ vol_type; int usable_leb_size; } ;
struct ubi_device {int /*<<< orphan*/  min_io_size; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ UBI_DYNAMIC_VOLUME ; 
 int /*<<< orphan*/  dbg_gen (char*,int) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int ubi_calc_data_len (struct ubi_device*,void*,int) ; 
 int ubi_eba_write_leb (struct ubi_device*,struct ubi_volume*,int,void*,int /*<<< orphan*/ ,int) ; 
 int ubi_eba_write_leb_st (struct ubi_device*,struct ubi_volume*,int,void*,int,int) ; 

__attribute__((used)) static int write_leb(struct ubi_device *ubi, struct ubi_volume *vol, int lnum,
		     void *buf, int len, int used_ebs)
{
	int err;

	if (vol->vol_type == UBI_DYNAMIC_VOLUME) {
		int l = ALIGN(len, ubi->min_io_size);

		memset(buf + len, 0xFF, l - len);
		len = ubi_calc_data_len(ubi, buf, l);
		if (len == 0) {
			dbg_gen("all %d bytes contain 0xFF - skip", len);
			return 0;
		}

		err = ubi_eba_write_leb(ubi, vol, lnum, buf, 0, len);
	} else {
		/*
		 * When writing static volume, and this is the last logical
		 * eraseblock, the length (@len) does not have to be aligned to
		 * the minimal flash I/O unit. The 'ubi_eba_write_leb_st()'
		 * function accepts exact (unaligned) length and stores it in
		 * the VID header. And it takes care of proper alignment by
		 * padding the buffer. Here we just make sure the padding will
		 * contain zeros, not random trash.
		 */
		memset(buf + len, 0, vol->usable_leb_size - len);
		err = ubi_eba_write_leb_st(ubi, vol, lnum, buf, len, used_ebs);
	}

	return err;
}