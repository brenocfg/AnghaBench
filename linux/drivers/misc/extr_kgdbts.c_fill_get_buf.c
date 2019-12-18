#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 char* get_buf ; 
 char hex_asc_hi (unsigned char) ; 
 char hex_asc_lo (unsigned char) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 TYPE_1__ ts ; 
 int /*<<< orphan*/  v2printk (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void fill_get_buf(char *buf)
{
	unsigned char checksum = 0;
	int count = 0;
	char ch;

	strcpy(get_buf, "$");
	strcat(get_buf, buf);
	while ((ch = buf[count])) {
		checksum += ch;
		count++;
	}
	strcat(get_buf, "#");
	get_buf[count + 2] = hex_asc_hi(checksum);
	get_buf[count + 3] = hex_asc_lo(checksum);
	get_buf[count + 4] = '\0';
	v2printk("get%i: %s\n", ts.idx, get_buf);
}