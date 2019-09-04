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
struct io_thread_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int os_read_file (int,char*,int) ; 

__attribute__((used)) static int bulk_req_safe_read(
	int fd,
	struct io_thread_req * (*request_buffer)[],
	struct io_thread_req **remainder,
	int *remainder_size,
	int max_recs
	)
{
	int n = 0;
	int res = 0;

	if (*remainder_size > 0) {
		memmove(
			(char *) request_buffer,
			(char *) remainder, *remainder_size
		);
		n = *remainder_size;
	}

	res = os_read_file(
			fd,
			((char *) request_buffer) + *remainder_size,
			sizeof(struct io_thread_req *)*max_recs
				- *remainder_size
		);
	if (res > 0) {
		n += res;
		if ((n % sizeof(struct io_thread_req *)) > 0) {
			/*
			* Read somehow returned not a multiple of dword
			* theoretically possible, but never observed in the
			* wild, so read routine must be able to handle it
			*/
			*remainder_size = n % sizeof(struct io_thread_req *);
			WARN(*remainder_size > 0, "UBD IPC read returned a partial result");
			memmove(
				remainder,
				((char *) request_buffer) +
					(n/sizeof(struct io_thread_req *))*sizeof(struct io_thread_req *),
				*remainder_size
			);
			n = n - *remainder_size;
		}
	} else {
		n = res;
	}
	return n;
}