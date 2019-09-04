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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u32 ;
struct firmware {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static u32 slic_read_dword_from_firmware(const struct firmware *fw, int *offset)
{
	int idx = *offset;
	__le32 val;

	memcpy(&val, fw->data + *offset, sizeof(val));
	idx += 4;
	*offset = idx;

	return le32_to_cpu(val);
}