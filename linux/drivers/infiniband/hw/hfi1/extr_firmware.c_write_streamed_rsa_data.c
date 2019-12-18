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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_streamed_rsa_data(struct hfi1_devdata *dd, int what,
				    const u8 *data, int nbytes)
{
	u64 *ptr = (u64 *)data;
	int qw_size = nbytes / 8;

	for (; qw_size > 0; qw_size--, ptr++)
		write_csr(dd, what, *ptr);
}