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
struct asymmetric_key_id {size_t len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int hex2bin (int /*<<< orphan*/ ,char const*,size_t) ; 

inline int __asymmetric_key_hex_to_key_id(const char *id,
				   struct asymmetric_key_id *match_id,
				   size_t hexlen)
{
	match_id->len = hexlen;
	return hex2bin(match_id->data, id, hexlen);
}