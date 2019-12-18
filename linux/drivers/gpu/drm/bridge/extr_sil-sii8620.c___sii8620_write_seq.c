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
typedef  int /*<<< orphan*/  u16 ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void __sii8620_write_seq(struct sii8620 *ctx, const u16 *seq, int len)
{
	int i;

	for (i = 0; i < len; i += 2)
		sii8620_write(ctx, seq[i], seq[i + 1]);
}