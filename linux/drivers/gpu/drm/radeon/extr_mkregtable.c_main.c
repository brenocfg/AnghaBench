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
struct table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ parser_auth (struct table*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  table_init (struct table*) ; 
 int /*<<< orphan*/  table_print (struct table*) ; 

int main(int argc, char *argv[])
{
	struct table t;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <authfile>\n", argv[0]);
		exit(1);
	}
	table_init(&t);
	if (parser_auth(&t, argv[1])) {
		fprintf(stderr, "Failed to parse file %s\n", argv[1]);
		return -1;
	}
	table_print(&t);
	return 0;
}