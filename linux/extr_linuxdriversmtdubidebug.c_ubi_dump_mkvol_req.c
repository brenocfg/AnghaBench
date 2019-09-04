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
struct ubi_mkvol_req {char* vol_id; char* alignment; char* vol_type; char* name_len; int /*<<< orphan*/  name; scalar_t__ bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

void ubi_dump_mkvol_req(const struct ubi_mkvol_req *req)
{
	char nm[17];

	pr_err("Volume creation request dump:\n");
	pr_err("\tvol_id    %d\n",   req->vol_id);
	pr_err("\talignment %d\n",   req->alignment);
	pr_err("\tbytes     %lld\n", (long long)req->bytes);
	pr_err("\tvol_type  %d\n",   req->vol_type);
	pr_err("\tname_len  %d\n",   req->name_len);

	memcpy(nm, req->name, 16);
	nm[16] = 0;
	pr_err("\t1st 16 characters of name: %s\n", nm);
}