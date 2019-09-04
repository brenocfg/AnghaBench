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
struct sbefifo {int dummy; } ;
struct iov_iter {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int sbefifo_read_response (struct sbefifo*,struct iov_iter*) ; 
 int sbefifo_send_command (struct sbefifo*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int sbefifo_do_command(struct sbefifo *sbefifo,
			      const __be32 *command, size_t cmd_len,
			      struct iov_iter *response)
{
	/* Try sending the command */
	int rc = sbefifo_send_command(sbefifo, command, cmd_len);
	if (rc)
		return rc;

	/* Now, get the response */
	return sbefifo_read_response(sbefifo, response);
}