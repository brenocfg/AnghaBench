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
typedef  int /*<<< orphan*/  u32 ;
struct sbefifo {int /*<<< orphan*/  fsi_dev; } ;
typedef  int /*<<< orphan*/  raw_word ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int fsi_device_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sbefifo_regr(struct sbefifo *sbefifo, int reg, u32 *word)
{
	__be32 raw_word;
	int rc;

	rc = fsi_device_read(sbefifo->fsi_dev, reg, &raw_word,
			     sizeof(raw_word));
	if (rc)
		return rc;

	*word = be32_to_cpu(raw_word);

	return 0;
}