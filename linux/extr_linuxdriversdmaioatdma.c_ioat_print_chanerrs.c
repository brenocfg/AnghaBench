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
struct ioatdma_chan {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * chanerr_str ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dev (struct ioatdma_chan*) ; 

__attribute__((used)) static void ioat_print_chanerrs(struct ioatdma_chan *ioat_chan, u32 chanerr)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(chanerr_str); i++) {
		if ((chanerr >> i) & 1) {
			dev_err(to_dev(ioat_chan), "Err(%d): %s\n",
				i, chanerr_str[i]);
		}
	}
}