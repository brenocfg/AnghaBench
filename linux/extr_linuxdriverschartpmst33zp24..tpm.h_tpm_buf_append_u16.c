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
typedef  int /*<<< orphan*/  u16 ;
struct tpm_buf {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tpm_buf_append (struct tpm_buf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void tpm_buf_append_u16(struct tpm_buf *buf, const u16 value)
{
	__be16 value2 = cpu_to_be16(value);

	tpm_buf_append(buf, (u8 *) &value2, 2);
}